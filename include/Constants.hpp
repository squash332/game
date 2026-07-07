#pragma once

// WINDOW
constexpr int VIRTUAL_WIDTH  = 320;
constexpr int VIRTUAL_HEIGHT = 180;
constexpr int TILE_SIZE      = 32;

// BUTTONS
constexpr int BUTTON_HEIGHT = 64;
constexpr int BUTTON_WIDTH = 64;

// TEXTBOX
constexpr int TEXTBOX_PADDING     = 10;
constexpr int TEXTBOX_HEIGHT      = 50;
constexpr int TEXTBOX_FONT_SIZE   = 10;
constexpr int TEXTBOX_TEXT_OFFSET = 15;

// FONT SIZES
constexpr int FONT_SIZE_BIG    = 40;
constexpr int FONT_SIZE_MEDIUM = 20;
constexpr int FONT_SIZE_SMALL  = 10;

// TEXT POSITIONS (Y only, X is runtime via MeasureText)
constexpr int TEXT_TOP_MIDDLE_Y = TEXTBOX_HEIGHT;
constexpr int TEXT_MIDDLE_Y   = VIRTUAL_HEIGHT / 2;
constexpr int TEXT_BOTTOM_Y   = VIRTUAL_HEIGHT - FONT_SIZE_SMALL - TEXTBOX_PADDING;
constexpr int TEXT_DIALOGUE_Y = VIRTUAL_HEIGHT - TEXTBOX_HEIGHT + TEXTBOX_TEXT_OFFSET;

// TEXT ANIMATION SPEEDS
constexpr int TEXT_SPEED_INSTANT = 1;
constexpr int TEXT_SPEED_FAST   = 2;
constexpr int TEXT_SPEED_NORMAL = 5;
constexpr int TEXT_SPEED_SLOW   = 12;
constexpr int LINE_DELAY = 60;