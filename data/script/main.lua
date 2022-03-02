local hello_texture = {}
local hello_font = {}
local hello_drawer = {}

function setup()
    hello_texture = texture()
    hello_drawer = draw2d(hello_texture)
    hello_drawer.scale = vector2(1, 1)
    hello_font = font()
    hello_font:load(DEFAULT_FONT, 128)
    hello_font:render_text(hello_texture, "Hello World!", color(1, 1, 1, 1), 2,
                           color(1, 1, 1, 1))

end

function update() hello_drawer:draw() end
