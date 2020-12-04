#pragma once

#ifdef BLITZENGINE__EXPORTS
#define BLITZENGINE_API __declspec(dllexport)
#else
#define BLITZENGINE_API __declspec(dllimport)
#endif // BLITZENGINE__EXPORTS
