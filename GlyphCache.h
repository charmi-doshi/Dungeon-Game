#pragma once
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <unordered_map>

class GlyphCache
{
public:
    GlyphCache(SDL_Renderer* renderer, const char* fontPath, int ptSize);
    ~GlyphCache();

    void draw(SDL_Renderer* renderer, char glyph,
        int col, int row, SDL_Color color) const;

private:
    TTF_Font* font_ = nullptr;
    SDL_Texture* atlas_ = nullptr;   // not used in this simple version
    SDL_Renderer* renderer_ = nullptr;

    struct GlyphEntry
    {
        SDL_Texture* tex = nullptr;
        int          w = 0;
        int          h = 0;
    };

    mutable std::unordered_map<char, GlyphEntry> cache_;
    const GlyphEntry& getGlyph(char c) const;
};

void GlyphCache::draw(SDL_Renderer* renderer, char glyph,
    int col, int row, SDL_Color color) const
{
    const GlyphEntry& g = getGlyph(glyph);
    SDL_SetTextureColorMod(g.tex, color.r, color.g, color.b);
    SDL_SetTextureAlphaMod(g.tex, color.a);

    float x = col * CELL_W + (CELL_W - g.w) * 0.5f;
    float y = row * CELL_H + (CELL_H - g.h) * 0.5f;
    SDL_FRect dst{ x, y, (float)g.w, (float)g.h };
    SDL_RenderTexture(renderer, g.tex, nullptr, &dst);
}
