#include "EMU.h"
#include "../../ui/state.h"
#include "../../ui/views/main_screen/bottom_row/submenus/log/log_component.h"
#include "../CART/CART.h"

// SDL3
#include "SDL3/SDL_init.h"
#include "SDL3/SDL_keycode.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_video.h>

using namespace UIState;

int EMU::START_ROM(string file_name, string &error_message) {

  // Create cartridge object and load rom data
  CART *cartridge = new CART();
  cartridge->READ_ROM(file_name);

  // Create SDL3 OpenGL compatible window to handle video, audio, input, etc and
  // init
  SDL_Window *sakura_window;
  if (SDL_Init(SDL_INIT_VIDEO)) {
    error_message = I18nObject.tr("ERROR_INITIALIZING_SDL");
    return -1;
  }
  sakura_window = SDL_CreateWindow("sakura-v2", 500, 500, 0);

  // Main emu loop var
  bool emu_running = true;

  // TODO: Explain why Im using FillSurfaceRect
  SDL_Surface *sakura_surface = SDL_GetWindowSurface(sakura_window);
  uint32_t red = SDL_MapSurfaceRGB(sakura_surface, 0xFF, 0x00, 0x00);
  SDL_FillSurfaceRect(sakura_surface, NULL, red);
  SDL_UpdateWindowSurface(sakura_window);

  // If there's an error creating the window
  if (sakura_window == NULL) {
    error_message = I18nObject.tr("ERROR_CREATING_WINDOW");
    return -1;
  }

  // Main emulation loop
  while (emu_running) {

    SDL_Event sakura_event;

    // Right now the CPU isn't set up, so its just pollilng for escape key
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
