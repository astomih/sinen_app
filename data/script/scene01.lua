local utility = require("utility")

hello_texture = {}
function setup()
    print("scene01.lua: setup()")
    hello_texture = create_texture()
    texture_fill_color(hello_texture, color.new(1, 1, 0, 1), "red")

    print("scene01.lua: end setup()")
end

function update()

    hello_drawer = draw2d_object.new()
    hello_drawer.texture = hello_texture
    hello_drawer.position = vector2.new(100, 0)
    hello_drawer.scale = vector2.new(200, 200)
    hello_drawer.rotation = 0
    draw2d.rect(hello_drawer)
    print("scene01.lua: update()")
end
