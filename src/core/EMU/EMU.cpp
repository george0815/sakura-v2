#include "EMU.h"
#include "../../ui/views/main_screen/bottom_row/submenus/log/log_component.h"
#include "../CART/CART.h"
#include "SDL3/SDL_events.h"
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keycode.h"
#include "SDL3/SDL_render.h"
#include "SDL3/SDL_surface.h"
#include "SDL3/SDL_timer.h"

// SDL3
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>
#include <cstdint>

int EMU::START_ROM(string file_name) {

  CART *cartridge = new CART();

  cartridge->READ_ROM(file_name);

  // Create SDL3 OpenGL compatible window to handle video, audio, input, etc and
  // init
  SDL_Window *sakura_window;
  bool emu_running = true;
  SDL_Init(SDL_INIT_VIDEO);

  sakura_window = SDL_CreateWindow("sakura-v2", 500, 500, 0);

  SDL_Surface *sakura_surface = SDL_GetWindowSurface(sakura_window);

  uint32_t red = SDL_MapSurfaceRGB(sakura_surface, 0xFF, 0x00, 0x00);
  SDL_FillSurfaceRect(sakura_surface, NULL, red);

  SDL_UpdateWindowSurface(sakura_window);

  if (sakura_window == NULL) {
    // TODO: error_handling
    LogComponent::AddLogEntry("ERROR CREATING WINDOW");
  }

  LogComponent::AddLogEntry("Create window");

  while (emu_running) {

    SDL_Event sakura_event;

    while (SDL_PollEvent(&sakura_event)) {
      if (sakura_event.type == SDL_EVENT_KEY_DOWN) {
        if (sakura_event.key.key == SDLK_ESCAPE) {
          emu_running = false;
          SDL_DestroyWindow(sakura_window);
          SDL_Quit();
        }
      }
    }
  }
  return 0;
}
