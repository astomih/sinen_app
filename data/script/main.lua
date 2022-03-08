local hello_texture = {}
local hello_font = {}
local hello_drawer = {}

function setup()
    hello_texture = texture()
    hello_drawer = draw2d(hello_texture)
    hello_font = font()
    hello_font:load(DEFAULT_FONT, 128)
    hello_font:render_text(hello_texture, "Hello Sinen World!",
                           color(1, 1, 1, 1), 2, color(1, 1, 1, 1))
    hello_drawer.scale = hello_texture:size()
    hello_drawer.position = vector2(0, 0)
end

function update()
    hello_drawer:draw()
    if keyboard:is_key_down(keySPACE) then change_scene("stage") end
end
