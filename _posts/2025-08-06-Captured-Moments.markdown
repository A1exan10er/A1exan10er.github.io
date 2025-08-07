---
title: "Captured Moments"
layout: single
date: 2025-08-06
author: tianyu
categories: [gallery]
tags: [photos, gallery]
classes: wide
excerpt: "A collection of photos from my travel adventures."
header:
  overlay_image: /assets/images/gallery/IMG_3537.JPEG
  overlay_filter: 0.3
  caption: "Captured moments in nature and city life"
  actions:
    - label: "Back to Home"
      url: "/"
lightbox: true
---

This post includes a collection of photos capturing moments from my travel adventures. Each image tells a story, reflecting the beauty and diversity of the places I've visited.

<div class="custom-gallery">
  <div class="gallery-item">
    <img src="/assets/images/gallery/IMG_3537.JPEG" alt="Oia, Santorini, Greece" title="Oia in Santorini">
    <p class="gallery-caption">Oia in Santorini</p>
  </div>
  <div class="gallery-item">
    <img src="/assets/images/gallery/IMG_3989.JPEG" alt="The Academy of Athens, Greece" title="The Academy of Athens">
    <p class="gallery-caption">The Academy of Athens</p>
  </div>
  <div class="gallery-item">
    <img src="/assets/images/gallery/IMG_3997.JPEG" alt="The Academy of Athens, Greece" title="Rooftop of the Academy">
    <p class="gallery-caption">Rooftop of the Academy</p>
  </div>
</div>

<style>
.custom-gallery {
  display: grid;
  grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
  gap: 20px;
  margin: 20px 0;
}

.gallery-item {
  text-align: center;
}

.gallery-item img {
  width: 100%;
  height: auto;
  border-radius: 8px;
  cursor: pointer;
  transition: transform 0.3s ease;
}

.gallery-item img:hover {
  transform: scale(1.02);
}

.gallery-caption {
  margin-top: 8px;
  font-style: italic;
  color: #666;
  font-size: 0.9em;
}
</style>

<script src="/assets/js/gallery-lightbox.js"></script>
