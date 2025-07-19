#include <poppler/glib/poppler.h>
#include <cairo.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <climits>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " input.pdf" << std::endl;
        return 1;
    }

    std::string pdf_path = argv[1];
    GError *error = nullptr;
    
    // Convert to absolute path and proper file URI
    char *absolute_path = realpath(pdf_path.c_str(), nullptr);
    if (!absolute_path) {
        std::cerr << "Failed to resolve path: " << pdf_path << std::endl;
        return 1;
    }
    
    gchar *file_uri = g_filename_to_uri(absolute_path, nullptr, &error);
    free(absolute_path);
    
    if (!file_uri) {
        std::cerr << "Failed to create file URI: " << pdf_path << std::endl;
        if (error) {
            std::cerr << "Error: " << error->message << std::endl;
            g_error_free(error);
        }
        return 1;
    }
    
    // Load PDF document
    PopplerDocument *doc = poppler_document_new_from_file(file_uri, nullptr, &error);
    g_free(file_uri);
    if (!doc) {
        std::cerr << "Failed to open PDF: " << pdf_path << std::endl;
        if (error) {
            std::cerr << "Error: " << error->message << std::endl;
            g_error_free(error);
        }
        return 1;
    }

    int num_pages = poppler_document_get_n_pages(doc);
    
    for (int i = 0; i < num_pages; ++i) {
        PopplerPage *page = poppler_document_get_page(doc, i);
        if (!page) continue;

        // Get page dimensions
        double width, height;
        poppler_page_get_size(page, &width, &height);
        
        // Create Cairo surface
        double scale = 2.0; // 2x scale for better quality
        int img_width = (int)(width * scale);
        int img_height = (int)(height * scale);
        
        cairo_surface_t *surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32, img_width, img_height);
        cairo_t *cr = cairo_create(surface);
        
        // Scale and render
        cairo_scale(cr, scale, scale);
        cairo_set_source_rgb(cr, 1.0, 1.0, 1.0); // White background
        cairo_paint(cr);
        
        poppler_page_render(page, cr);
        
        // Get image data
        cairo_surface_flush(surface);
        unsigned char *data = cairo_image_surface_get_data(surface);
        
        // Convert Cairo ARGB to OpenCV BGR
        cv::Mat mat(img_height, img_width, CV_8UC4, data);
        cv::Mat mat_bgr;
        cv::cvtColor(mat, mat_bgr, cv::COLOR_BGRA2BGR);
        
        // Save as JPG
        std::string out_name = "page_" + std::to_string(i + 1) + ".jpg";
        cv::imwrite(out_name, mat_bgr);
        std::cout << "Saved: " << out_name << std::endl;
        
        // Cleanup
        cairo_destroy(cr);
        cairo_surface_destroy(surface);
        g_object_unref(page);
    }

    g_object_unref(doc);
    return 0;
}