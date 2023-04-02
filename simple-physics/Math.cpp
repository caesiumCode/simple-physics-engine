#include "Math.hpp"

namespace sp
{

const Vector Vector::Zero = Vector(0, 0);

std::random_device          Random::rd;
std::default_random_engine  Random::re = std::default_random_engine(Random::rd());

}
