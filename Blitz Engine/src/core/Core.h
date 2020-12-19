#pragma once

#ifdef BLITZENGINE__EXPORTS
#define BLITZENGINE_API __declspec(dllexport)
#else
#define BLITZENGINE_API __declspec(dllimport)
#endif // BLITZENGINE__EXPORTS

#define BIND_FUNC(x) std::bind(&x, this, std::placeholders::_1)