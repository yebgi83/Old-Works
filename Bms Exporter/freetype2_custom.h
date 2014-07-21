#ifndef _SDL_H
#include <sdl.h>
#endif

#include <ft2build.h>
#include FT_FREETYPE_H

static char *DefErrMsgSection = "[FreeType2 Custom]";
#ifndef DECLARE_ERRMSG
   #define ERRMSG( condition, msg ) if( condition ){ fprintf( stderr, "%s %s\n", DefErrMsgSection, msg); exit(3); }
   #define DECLARE_ERRMSG
#endif

#define FT_COLOR_BLACK  0
#define FT_COLOR_WHITE  1
#define FT_COLOR_RED    2
#define FT_COLOR_GREEN  3
#define FT_COLOR_BLUE   4
#define FT_COLOR_YELLOW 5
#define FT_COLOR_AMBER  6
#define FT_COLOR_PINK   7
#define FT_CREATE_COLOR_TABLE( count, tr, tg, tb ) for( count = 1; count < 256; i ++ ) { FontColor[count].r = tr; FontColor[count].g = tg; FontColor[count].b = tb; }

FT_Library  Library;
FT_Face     Face;
FT_UInt16   FontSize = 16;
SDL_Color   FontColor[256];

char *DefFontFile = "default.ttf";
 
void SetFontColor( int color )
{
    int i;
    FontColor[0].r = FontColor[0].g = FontColor[0].b = 0;
    /* Fill colors with color information */
    switch( color )
    {
        case FT_COLOR_BLACK:
             FT_CREATE_COLOR_TABLE( i, 0, 0, 0 )
             break;
        case FT_COLOR_WHITE:
             FT_CREATE_COLOR_TABLE( i, i, i ,i )
             break;
        case FT_COLOR_RED:
             FT_CREATE_COLOR_TABLE( i, i, 0, 0 )
             break;
        case FT_COLOR_GREEN:
             FT_CREATE_COLOR_TABLE( i, 0, i, 0 )
             break;
        case FT_COLOR_BLUE:
             FT_CREATE_COLOR_TABLE( i, 0, 0, i )
             break;
        case FT_COLOR_YELLOW:
             FT_CREATE_COLOR_TABLE( i, i, i, 0 )
             break;
        case FT_COLOR_AMBER:
             FT_CREATE_COLOR_TABLE( i, i, i/4*3, i/6 )
             break;
        case FT_COLOR_PINK:
             FT_CREATE_COLOR_TABLE( i, i, 0, i )
             break;
    }
}

void SetFontSize( FT_UInt16 size )
{
    int error;
    FontSize = size;
    error = FT_Set_Pixel_Sizes( Face,   /* handle to face object */
                                FontSize,   /* pixel_width           */
                                FontSize ); /* pixel_height          */
    ERRMSG( error, "Error. FT_Set_Pixel_Size\n" );
}

SDL_Surface *CreateSurfaceFromFTBitmap( FT_Bitmap ftbmp )
{
    int i;
    SDL_Color   colors[256];
    SDL_Surface *convsurface = SDL_CreateRGBSurfaceFrom( (void *)ftbmp.buffer,
                                                         ftbmp.width,
                                                         ftbmp.rows,
                                                         8,
                                                         ftbmp.pitch,
                                                         0x000000ff,
                                                         0x0000ff00,
                                                         0x00ff0000,
                                                         0xff000000 );

    /* Set palette */
    SDL_SetColors( convsurface, FontColor, 1, 256 );

    /* Set color key */
    SDL_SetColorKey( convsurface, SDL_SRCCOLORKEY, 0 );
    
    return convsurface;
}

void OpenFontFile( char *fontfilename )
{
    int error;
    error = FT_New_Face( Library,
                         fontfilename,
                         0,
                         &Face );
    ERRMSG( error == FT_Err_Unknown_File_Format, "The font file could be opened and read, but it appears that its font format is unsupported." );
    ERRMSG( error && (error != FT_Err_Unknown_File_Format), "The file could't be opened." );

    error = FT_Set_Char_Size( Face,    /* handle to face object           */
                                 0,    /* char_width in 1/64th of points  */
                             16*64,    /* char_height in 1/64th of points */
                               300,    /* horizontal device resolution    */
                               300 );  /* vertical device resolution      */
    ERRMSG( error, "Error. FT_Set_Char_Size\n" );

    FT_Select_Charmap( Face, FT_ENCODING_WANSUNG );
}
 
void InitFreeType2( void )
{
    ERRMSG( FT_Init_FreeType( &Library ), "An error occurred during library initialization." );
    OpenFontFile( DefFontFile );
    SetFontSize(FontSize);
    SetFontColor( FT_COLOR_WHITE );
}

void DrawText( SDL_Surface *surface, int x, int y, char *fmt, ... )
{
    int n, error;
    char text[256];
    FT_GlyphSlot slot = Face->glyph;  

    va_list valist;
    va_start( valist, fmt );    
    vsprintf( text, fmt, valist );
    va_end(valist);

    for( n = 0 ; n < strlen(text); )
    {
        FT_ULong glyph_index;
        SDL_Surface *tempsurface;

        /* retrieve glyph index from character code */
        if( (text[n] & 128) && (text[n+1] & 128) ) 
        {
            FT_UInt16 code = *((FT_UInt16 *)(text+n));
            /* Exchange upper char and lower char, because of wansung font format */
            code = ((code & 0xff) << 8) | ((code & 0xff00) >> 8);
            glyph_index = FT_Get_Char_Index( Face, code );
            n += 2;
        }
        else
            glyph_index = FT_Get_Char_Index( Face, text[n++] );
         
        /* load glyph image into the slot (erase previous one) */
        error = FT_Load_Glyph( Face, glyph_index, FT_LOAD_DEFAULT );
        if ( error ) continue;  /* ignore errors */

        /* convert to an anti-aliased bitmap */
        error = FT_Render_Glyph( Face->glyph, FT_RENDER_MODE_NORMAL );
        if ( error ) continue;

        /* now, draw to our target surface */
        tempsurface = CreateSurfaceFromFTBitmap( slot->bitmap );
        if( tempsurface ) 
        {
            SDL_Rect drawrect;
            drawrect.x = x + slot->bitmap_left,
            drawrect.y = y - slot->bitmap_top + FontSize;
            drawrect.w = (slot->bitmap).width;
            drawrect.h = (slot->bitmap).rows;
            SDL_BlitSurface( tempsurface, 0, surface, &drawrect );
            SDL_FreeSurface( tempsurface );
        }
        x += slot->advance.x >> 6;
        y += slot->advance.y >> 6;
    }
}
 
void _GetTrueTypeStringSize( int *w, int *h, char *fmt, ... )
{
    int n, error;
    char text[256];
    FT_GlyphSlot slot = Face->glyph;  
    *w = *h = 0;
    
    va_list valist;
    va_start( valist, fmt );    
    vsprintf( text, fmt, valist );
    va_end(valist);

    int yinc = 2;
    for( n = 0 ; n < strlen(text); )
    {
        FT_ULong glyph_index;
        SDL_Surface *tempsurface;

        /* retrieve glyph index from character code */
        if( (text[n] & 128) && (text[n+1] & 128) ) 
        {
            FT_UInt16 code = *((FT_UInt16 *)(text+n));
            /* Exchange upper char and lower char, because of wansung font format */
            code = ((code & 0xff) << 8) | ((code & 0xff00) >> 8);
            glyph_index = FT_Get_Char_Index( Face, code );
            n += 2;
        }
        else
            glyph_index = FT_Get_Char_Index( Face, text[n++] );
        
        /* load glyph image into the slot (erase previous one) */
        error = FT_Load_Glyph( Face, glyph_index, FT_LOAD_DEFAULT );
        if ( error ) continue;  /* ignore errors */

        /* convert to an anti-aliased bitmap */
        error = FT_Render_Glyph( Face->glyph, FT_RENDER_MODE_NORMAL );
        if ( error ) continue;
   
        *w += slot->advance.x >> 6;
    }
    *h = FontSize;
}
 
SDL_Surface *CreateTrueTypeStringSurface( char *fmt, ... )
{
    int w, h;
    char text[256];
    SDL_Surface *ttsurface;

    va_list valist;
    va_start( valist, fmt );    
    vsprintf( text, fmt, valist );
    va_end(valist);
    
    _GetTrueTypeStringSize( &w, &h, text );
    
    // 16bit mask
    // 1111 1000 0000 0000
    // 0000 0111 1110 0000
    // 0000 0000 0001 1111

    w += 2;
    h = FontSize + 2;
    ttsurface = SDL_CreateRGBSurface( SDL_SWSURFACE, 
                                      w, h, 16,
                                      0xf800,
                                      0x07e0,
                                      0x001f,
                                      0x0000 );

    DrawText( ttsurface, 0, 0, text );
    return( ttsurface );                                      
}            
