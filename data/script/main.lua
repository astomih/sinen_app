local hello_drawer = {}
local hello_drawer2 = {}
local hello_drawer3 = {}
local hello_texture = {}
local hello_texture2 = {}
local hello_font = {}
local vmusic = {}
local vsound = {}

function setup()
    hello_texture = texture()
    hello_texture:load("rect.png")
    -- hello_texture:fill_color(color(1, 1, 1, 1))
    hello_texture2 = texture()
    hello_drawer = draw2d(hello_texture2)
    hello_drawer.scale = vector2(1, 1)
    hello_font = font()
    hello_font:load("mplus/mplus-1p-medium.ttf", 128)
    hello_font:render_text(hello_texture2, "Hello World!", color(1, 1, 1, 1), 2,
                           color(1, 1, 1, 1))

    hello_drawer.position = vector2(0, 0)
    hello_drawer.rotation = 0

    hello_drawer2 = draw2d(hello_texture)
    hello_drawer2.position = vector2(0, 0)
    hello_drawer2.scale = vector2(100, 100)
    hello_drawer2.rotation = 0

    hello_drawer3 = draw3d(hello_texture)
    hello_drawer3.position = vector3(1, 0, 0)
    hello_drawer3.scale = vector3(1, 1, 1)
    hello_drawer3.rotation = vector3(0, 0, 0)

    vmusic = music()
    vmusic:load("Stage1.ogg")
    vmusic:play()

    vsound = sound()
    vsound:load("shot.wav")
end

function update()
    if keyboard:is_key_down(keySPACE) then
        hello_drawer.rotation = hello_drawer.rotation + 2 * delta_time
        hello_drawer2.rotation = hello_drawer2.rotation + 5 * delta_time

        -- hello_drawer3:draw()
        hello_drawer3.rotation.z = hello_drawer3.rotation.z + 5 * delta_time
        -- body
    end
    if keyboard:get_key_state(keyZ) == buttonPRESSED then vsound:play() end
    hello_drawer:draw()
    hello_drawer2.position.x = (mouse:get_position().x - 640) * 2
    hello_drawer2.position.y = -(mouse:get_position().y - 780 / 2) * 2
    hello_drawer2:draw()
end
