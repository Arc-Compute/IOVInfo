// This source file contains the implementation of the functions declared in inc/drm_helper.h.

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <xf86drm.h>
#include <xf86drmMode.h>
#include "../inc/drm_helper.h"

// This function opens the Direct Rendering Manager (DRM) file descriptor.
// This is how we control the GPU.
int open_drm_file_descriptor() {
    int drm_fd = open("/dev/dri/card0", O_RDWR | O_NONBLOCK);
    if (drm_fd < 0) {
        perror("Unable to open the Direct Rendering Manager file descriptor.");
        return -1;
    }
    return drm_fd;
}

// Here we obtain the DRM Resources as drmModeRes using the DRM file descriptor.
drmModeRes* get_drm_resources(int drm_fd) {
    drmModeRes* resources = drmModeGetResources(drm_fd);
    if (!resources) {
        perror("Failed to get Direct Rendering Manager resources");
        return NULL;
    }
    return resources;
}

// This function prints the Direct Rendering Manager resources.
void print_resources(drmModeRes* resources) {
    printf("Connectors: %d\n", resources->count_connectors);
    printf("Encoders: %d\n", resources->count_encoders);
    printf("CRTCs: %d\n", resources->count_crtcs);
    printf("Framebuffers: %d\n", resources->count_fbs);
}

// This function obtains the Direct Rendering Manager connector information using the DRM file descriptor.
drmModeConnector* get_drm_connector(int drm_fd, uint32_t connector_id) {
    drmModeConnector* connector = drmModeGetConnector(drm_fd, connector_id);
    if (!connector) {
        perror("Failed to get Direct Rendering Manager connector");
        return NULL;
    }
    return connector;
}

// This function prints the Direct Rendering Manager connector.
void print_connector(drmModeConnector* connector, int index) {
    printf("Connector %d:\n", index);
    printf("\tID: %d\n", connector->connector_id);
    printf("\tType: %d\n", connector->connector_type);
    printf("\tType ID: %d\n", connector->connector_type_id);
    printf("\tEncoder ID: %d\n", connector->encoder_id);
    printf("\tConnection: %d\n", connector->connection);
    if (connector->count_modes > 0) {
        printf("\tSize: %dx%d\n", connector->modes[0].hdisplay, connector->modes[0].vdisplay);
    } else {
        printf("\tSize: N/A\n");
    }
    printf("\tModes: %d\n", connector->count_modes);
    printf("\tProps: %d\n", connector->count_props);
    printf("\tEncoders: %d\n", connector->count_encoders);
}

void free_drm_connector(drmModeConnector* connector) {
    drmModeFreeConnector(connector);
}

// This function obtains the Direct Rendering Manager encoder information using the DRM file descriptor.
drmModeEncoder* get_drm_encoder(int drm_fd, uint32_t encoder_id) {
    drmModeEncoder* encoder = drmModeGetEncoder(drm_fd, encoder_id);
    if (!encoder) {
        perror("Failed to get Direct Rendering Manager encoder");
        return NULL;
    }
    return encoder;
}

// This function prints the Direct Rendering Manager encoder.
void print_encoder(drmModeEncoder* encoder, int index) {
    printf("Encoder %d:\n", index);
    printf("\tID: %d\n", encoder->encoder_id);
    printf("\tType: %d\n", encoder->encoder_type);
    printf("\tCRTC ID: %d\n", encoder->crtc_id);
    printf("\tPossible CRTCs: %d\n", encoder->possible_crtcs);
    printf("\tPossible Clones: %d\n", encoder->possible_clones);
}

// This function frees the Direct Rendering Manager encoder.
void free_drm_encoder(drmModeEncoder* encoder) {
    drmModeFreeEncoder(encoder);
}

// This function obtains the Direct Rendering Manager CRTC information using the DRM file descriptor.
drmModeCrtc* get_drm_crtc(int drm_fd, uint32_t crtc_id) {
    drmModeCrtc* crtc = drmModeGetCrtc(drm_fd, crtc_id);
    if (!crtc) {
        perror("Failed to get Direct Rendering Manager CRTC");
        return NULL;
    }
    return crtc;
}

// This function prints the Direct Rendering Manager CRTC.
void print_crtc(drmModeCrtc* crtc, int index) {
    printf("CRTC %d:\n", index);
    printf("\tID: %d\n", crtc->crtc_id);
    printf("\tBuffer ID: %d\n", crtc->buffer_id);
    printf("\tX: %d\n", crtc->x);
    printf("\tY: %d\n", crtc->y);
    printf("\tWidth: %d\n", crtc->width);
    printf("\tHeight: %d\n", crtc->height);
    printf("\tMode Valid: %d\n", crtc->mode_valid);
    printf("\tMode: %dx%d\n", crtc->mode.hdisplay, crtc->mode.vdisplay);
    printf("\tGamma Size: %d\n", crtc->gamma_size);
}

// This function frees the Direct Rendering Manager CRTC.
void free_drm_crtc(drmModeCrtc* crtc) {
    drmModeFreeCrtc(crtc);
}

// This function obtains the Direct Rendering Manager framebuffer information using the DRM file descriptor.
drmModeFB* get_drm_framebuffer(int drm_fd, uint32_t fb_id) {
    drmModeFB* fb = drmModeGetFB(drm_fd, fb_id);
    if (!fb) {
        perror("Failed to get Direct Rendering Manager framebuffer");
        return NULL;
    }
    return fb;
}

// This function prints the Direct Rendering Manager framebuffer.
void print_framebuffer(drmModeFB* fb, int index) {
    printf("Framebuffer %d:\n", index);
    printf("\tID: %d\n", fb->fb_id);
    printf("\tWidth: %d\n", fb->width);
    printf("\tHeight: %d\n", fb->height);
    printf("\tPitch: %d\n", fb->pitch);
    printf("\tDepth: %d\n", fb->depth);
    printf("\tBPP: %d\n", fb->bpp);
    printf("\tHandle: %d\n", fb->handle);
}

// This function frees the Direct Rendering Manager framebuffer.
void free_drm_framebuffer(drmModeFB* fb) {
    drmModeFreeFB(fb);
}

// This function closes the Direct Rendering Manager file descriptor.
void close_drm_file_descriptor(int drm_fd) {
    close(drm_fd);
}

// This function frees the Direct Rendering Manager resources.
void cleanup_drm_resources(int drm_fd, drmModeRes* resources) {
    drmModeFreeResources(resources);
    close_drm_file_descriptor(drm_fd);
}
