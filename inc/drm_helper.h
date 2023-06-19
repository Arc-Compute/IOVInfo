// This source file defines helper functions for interacting with the DRM subsystem.
// The functions are implemented in src/drm_helper.c.

#ifndef DRM_HELPER_H
#define DRM_HELPER_H

#include <xf86drmMode.h>

int open_drm_file_descriptor();
drmModeRes* get_drm_resources(int drm_fd);
void print_resources(drmModeRes* resources);
drmModeConnector* get_drm_connector(int drm_fd, uint32_t connector_id);
void print_connector(drmModeConnector* connector, int index);
void free_drm_connector(drmModeConnector* connector);
drmModeEncoder* get_drm_encoder(int drm_fd, uint32_t encoder_id);
void print_encoder(drmModeEncoder* encoder, int index);
void free_drm_encoder(drmModeEncoder* encoder);
drmModeCrtc* get_drm_crtc(int drm_fd, uint32_t crtc_id);
void print_crtc(drmModeCrtc* crtc, int index);
void free_drm_crtc(drmModeCrtc* crtc);
drmModeFB* get_drm_framebuffer(int drm_fd, uint32_t fb_id);
void print_framebuffer(drmModeFB* fb, int index);
void free_drm_framebuffer(drmModeFB* fb);
void close_drm_file_descriptor(int drm_fd);
void cleanup_drm_resources(int drm_fd, drmModeRes* resources);

#endif  // DRM_HELPER_H
