#ifdef _WIN32
#include <windows.h>
#include <filesystem>
#define PATH_MAX MAX_PATH
#else
#include <unistd.h>
#include <climits>
#endif

#include <poppler/cpp/poppler-document.h>
#include <poppler/cpp/poppler-page.h>
#include <poppler/cpp/poppler-page-renderer.h>
#include <poppler/cpp/poppler-image.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cstdlib>

std::string get_absolute_path(const std::string& path) {
#ifdef _WIN32
    char absolute_path[PATH_MAX];
    if (GetFullPathNameA(path.c_str(), PATH_MAX, absolute_path, NULL) == 0) {
        return "";
    }
    return std::string(absolute_path);
#else
    char* abs_path = realpath(path.c_str(), nullptr);
    if (!abs_path) return "";
    std::string result(abs_path);
    free(abs_path);
    return result;
#endif
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " input.pdf" << std::endl;
        return 1;
    }

    std::string pdf_path = argv[1];
    
    // Convert to absolute path
    std::string absolute_path = get_absolute_path(pdf_path);
    if (absolute_path.empty()) {
        std::cerr << "Failed to resolve path: " << pdf_path << std::endl;
        return 1;
    }

    // Load PDF document using poppler-cpp (more portable than poppler-glib)
    std::unique_ptr<poppler::document> doc(poppler::document::load_from_file(absolute_path));
    if (!doc) {
        std::cerr << "Failed to open PDF: " << pdf_path << std::endl;
        return 1;
    }

    int num_pages = doc->pages();
    poppler::page_renderer renderer;
    renderer.set_render_hint(poppler::page_renderer::antialiasing, true);
    renderer.set_render_hint(poppler::page_renderer::text_antialiasing, true);

    for (int i = 0; i < num_pages; ++i) {
        std::unique_ptr<poppler::page> page(doc->create_page(i));
        if (!page) continue;

        // Set resolution (DPI) for better quality
        double scale = 2.0; // 2x scale for better quality
        poppler::image img = renderer.render_page(page.get(), 
                                                  72.0 * scale, 72.0 * scale);
        
        if (!img.is_valid()) {
            std::cerr << "Failed to render page " << (i + 1) << std::endl;
            continue;
        }

        // Convert poppler image to OpenCV Mat
        int width = img.width();
        int height = img.height();
        
        // Poppler returns BGRA format
        cv::Mat mat(height, width, CV_8UC4, (void*)img.const_data());
        cv::Mat mat_bgr;
        cv::cvtColor(mat, mat_bgr, cv::COLOR_BGRA2BGR);

        // Save as JPG
        std::string out_name = "page_" + std::to_string(i + 1) + ".jpg";
        cv::imwrite(out_name, mat_bgr);
        std::cout << "Saved: " << out_name << std::endl;
    }

    return 0;
}
