#pragma once

#include "swRay.h"
#include "swCommons.h"

namespace sw {

class Camera {
  public:
    Camera() = default;
    Camera(Point3 lookFrom, Point3 lookAt, Vec3 vup, float vfov, float aspectRatio, float aperture, float focusDist) {
        // Camera set up
        float theta = degrees_to_radians(vfov);
        float h = tan(theta / 2);
        float viewportHeight = 2 * h;
        float viewportWidth = aspectRatio * viewportHeight;

        w = (lookFrom - lookAt).normalize();
        u = (vup % w).normalize();
        v = w % u;

        origin = lookFrom;
        horizontal = focusDist * viewportWidth * u;
        vertical = focusDist * viewportHeight * v;
        // This assigment starts scanning from top left, but it will be flipped later
        lowerLeft = origin - horizontal / 2 - vertical / 2 - focusDist * w;
        lensRadius = aperture / 2;
    }

      Ray get_ray(float s, float t) const {
            Vec3 rd = lensRadius * random_in_unit_disk();
            Vec3 offset = u * rd.x() + v * rd.y();
          return Ray(origin + offset, lowerLeft + s * horizontal + t * vertical - origin - offset);
      }

      private:
          Point3 origin;
          Vec3 horizontal;
          Vec3 vertical;
          Point3 lowerLeft;
          Vec3 u, v, w;
          float lensRadius;
};

} // namespace sw
