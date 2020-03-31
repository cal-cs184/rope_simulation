#ifndef CGL_SPECTRUM_H
#define CGL_SPECTRUM_H

#include "CGL.h"
#include "vector3D.h"

namespace CGL {

/**
 * Encodes radiance & irradiance values by the intensity of each visible
 * spectrum. Note that this is not strictly an actual spectrum with all
 * wavelengths, but it gives us enough information as we can only sense
 * a particular wavelengths.
 */

// Prints components
std::ostream &operator<<(std::ostream &os, const Spectrum &c);

}  // namespace CGL

#endif  // CGL_SPECTRUM_H
