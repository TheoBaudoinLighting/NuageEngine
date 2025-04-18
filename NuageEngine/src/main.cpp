#include "NuageEngine/NuageEngine.hpp"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include <glm/gtc/random.hpp>

using namespace glm;
using namespace Nuage;
using std::shared_ptr;
using std::make_shared;

int main() {
    const float aspect_ratio = 1.0f;
    const int image_width = 600;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 200;
    const int max_depth = 5;
    
    std::string output_filename = "render.ppm";
    std::ofstream output_file(output_filename);
    
    if (!output_file) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier " << output_filename << std::endl;
        return 1;
    }

    HittableList world;
    auto red = make_shared<Lambertian>(vec3(0.65f, 0.05f, 0.05f));
    auto green = make_shared<Lambertian>(vec3(0.12f, 0.45f, 0.15f));
    auto white = make_shared<Lambertian>(vec3(0.73f, 0.73f, 0.73f));
    auto light = make_shared<DiffuseLight>(vec3(15.0f, 15.0f, 15.0f));

    world.add(make_shared<YZRect>(0, 555, 0, 555, 555, green));
    world.add(make_shared<YZRect>(0, 555, 0, 555, 0, red, true));
    world.add(make_shared<XZRect>(213, 343, 227, 332, 554, light));
    world.add(make_shared<XZRect>(0, 555, 0, 555, 0, white, true));
    world.add(make_shared<XZRect>(0, 555, 0, 555, 555, white));
    world.add(make_shared<XYRect>(0, 555, 0, 555, 555, white));

    auto glass = make_shared<Dielectric>(1.5f);
    world.add(make_shared<Sphere>(vec3(190, 100, 190), 100, glass));
    world.add(make_shared<Sphere>(vec3(400, 100, 300), 100, glass));

    Camera cam(vec3(278, 278, -800), vec3(278, 278, 0), vec3(0, 1, 0), 40.0f, aspect_ratio, 0.0f, 800.0f);

    output_file << "P3\n" << image_width << " " << image_height << "\n255\n";
    
    int total_pixels = image_height * image_width;
    int pixels_done = 0;
    
    for (int j = image_height - 1; j >= 0; --j) {
        for (int i = 0; i < image_width; ++i) {
            vec3 color(0.0f);
            for (int s = 0; s < samples_per_pixel; ++s) {
                float u = (i + linearRand(0.0f, 1.0f)) / (image_width - 1);
                float v = (j + linearRand(0.0f, 1.0f)) / (image_height - 1);
                Ray r = cam.get_ray(u, v);
                color += ray_color(r, world, max_depth);
            }
            float scale = 1.0f / samples_per_pixel;
            float r = sqrtf(scale * color.r);
            float g = sqrtf(scale * color.g);
            float b = sqrtf(scale * color.b);
            int ir = static_cast<int>(256 * clampf(r, 0.0f, 0.999f));
            int ig = static_cast<int>(256 * clampf(g, 0.0f, 0.999f));
            int ib = static_cast<int>(256 * clampf(b, 0.0f, 0.999f));
            
            output_file << ir << ' ' << ig << ' ' << ib << '\n';
            
            pixels_done++;
            if (pixels_done % 10 == 0) {
                float pourcentage = 100.0f * pixels_done / total_pixels;
                std::cerr << "\rProgression: " << static_cast<int>(pourcentage) << "% ";
            }
        }
    }
    
    output_file.close();
    std::cerr << "\rRendu termine. Image sauvegardee dans " << output_filename << "                \n";
    return 0;
} 