// Gallery Lightbox functionality
// Automatically adds lightbox behavior to gallery images
document.addEventListener('DOMContentLoaded', function() {
  // Add lightbox functionality to gallery images
  const galleryImages = document.querySelectorAll('img');
  
  galleryImages.forEach(function(img) {
    // Only apply to images that are not the header image
    // Support both /assets/images/gallery/ and /assets/images/screenshots/
    if (img.src && (img.src.includes('/assets/images/gallery/') || img.src.includes('/assets/images/screenshots/')) && !img.closest('header')) {
      img.style.cursor = 'pointer';
      img.addEventListener('click', function(e) {
        e.preventDefault();
        e.stopPropagation();
        
        // Create lightbox overlay
        const overlay = document.createElement('div');
        overlay.style.cssText = `
          position: fixed;
          top: 0;
          left: 0;
          width: 100%;
          height: 100%;
          background: rgba(0, 0, 0, 0.8);
          display: flex;
          justify-content: center;
          align-items: center;
          z-index: 9999;
          cursor: pointer;
        `;
        
        // Create enlarged image
        const enlargedImg = document.createElement('img');
        enlargedImg.src = this.src;
        enlargedImg.style.cssText = `
          max-width: 90%;
          max-height: 90%;
          object-fit: contain;
          border-radius: 5px;
        `;
        
        overlay.appendChild(enlargedImg);
        document.body.appendChild(overlay);
        
        // Close lightbox when clicking overlay
        overlay.addEventListener('click', function() {
          document.body.removeChild(overlay);
        });
        
        // Close lightbox with Escape key
        document.addEventListener('keydown', function(e) {
          if (e.key === 'Escape' && document.body.contains(overlay)) {
            document.body.removeChild(overlay);
          }
        });
      });
    }
  });
});
