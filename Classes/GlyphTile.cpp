//
// Created by Jarad DeLorenzo on 2/8/16.
//

#include "GlyphTile.h"
#include "Globals.h"

using namespace lorafel;

bool lorafel::GlyphTile::init() {
  if(!Tile::init()) {
    return false;
  }

  setTag(Tag::GLYPH);
  initOptions();
  addEvents();
  return true;
}
