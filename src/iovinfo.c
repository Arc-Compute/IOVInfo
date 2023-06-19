// IOVInfo
// This program presents information about the IO devices, virtualization, and DRM resources on the system.

#include <stdio.h>
#include <stdlib.h>
#include "../inc/drm_helper.h"



int main() {
    // Here we'll open the DRM file descriptor.
    int drm_fd = open_drm_file_descriptor();
    if (drm_fd < 0) {
        return 1;
    }

    // Now we'll obtain the DRM Resources as drmModeRes using the DRM file descriptor.
    drmModeRes* resources = get_drm_resources(drm_fd);
    if (!resources) {
        close_drm_file_descriptor(drm_fd);
        return 1;
    }

    print_resources(resources);

    // Now we'll obtain the DRM connector information using the DRM file descriptor.
    for (int i = 0; i < resources->count_connectors; i++) {
        drmModeConnector* connector = get_drm_connector(drm_fd, resources->connectors[i]);
        if (!connector) {
            perror("Failed to get Direct Rendering Manager connector");
            cleanup_drm_resources(drm_fd, resources);
            return 1;
        }
        print_connector(connector, i);
        free_drm_connector(connector);
    }

    // Now we'll obtain the DRM encoder information using the DRM file descriptor.
    for (int i = 0; i < resources->count_encoders; i++) {
        drmModeEncoder* encoder = get_drm_encoder(drm_fd, resources->encoders[i]);
        if (!encoder) {
            perror("Failed to get Direct Rendering Manager encoder");
            cleanup_drm_resources(drm_fd, resources);
            return 1;
        }
        print_encoder(encoder, i);
        free_drm_encoder(encoder);
    }

    // Now we'll obtain the DRM CRTC information using the DRM file descriptor.
    for (int i = 0; i < resources->count_crtcs; i++) {
        drmModeCrtc* crtc = get_drm_crtc(drm_fd, resources->crtcs[i]);
        if (!crtc) {
            perror("Failed to get Direct Rendering Manager CRTC");
            cleanup_drm_resources(drm_fd, resources);
            return 1;
        }
        print_crtc(crtc, i);
        free_drm_crtc(crtc);
    }

    // Now we'll obtain the DRM framebuffer information using the DRM file descriptor.
    for (int i = 0; i < resources->count_fbs; i++) {
        drmModeFB* fb = get_drm_framebuffer(drm_fd, resources->fbs[i]);
        if (!fb) {
            perror("Failed to get Direct Rendering Manager framebuffer");
            cleanup_drm_resources(drm_fd, resources);
            return 1;
        }
        print_framebuffer(fb, i);
        free_drm_framebuffer(fb);
    }

    // Now we'll cleanup the DRM resources.
    cleanup_drm_resources(drm_fd, resources);

    return 0;
}
