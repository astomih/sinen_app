local hello_drawer = {}
local hello_drawer2 = {}
local hello_drawer3 = {}
local hello_texture = {}
local hello_texture2 = {}

function setup()
    hello_texture = texture()
    hello_texture:fill_color(color(1, 1, 1, 1))
    hello_texture2 = texture()
    hello_texture2:fill_color(color(1, 1, 1, 1))

    --   hello_drawer = draw2d(hello_texture)
    hello_drawer.position = vector2(0, 0)
    hello_drawer.scale = vector2(100, 100)
    hello_drawer.rotation = 0

    -- hello_drawer2 = draw2d(hello_texture)
    hello_drawer2.position = vector2(0, 0)
    hello_drawer2.scale = vector2(100, 100)
    hello_drawer2.rotation = 0

    hello_drawer3 = draw3d(hello_texture)
    hello_drawer3.position = vector3(1, 0, 0)
    hello_drawer3.scale = vector3(1, 1, 1)
    hello_drawer3.rotation = vector3(0, 0, 0)
end

function update()
    -- hello_drawer:draw()
    hello_drawer.rotation = hello_drawer.rotation + 2 * delta_time
    -- hello_drawer2:draw()
    hello_drawer2.rotation = hello_drawer2.rotation + 5 * delta_time

    hello_drawer3:draw()
    hello_drawer3.rotation.x = hello_drawer3.rotation.x + 5 * delta_time

end
