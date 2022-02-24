local utility = require("utility")

function setup()
    print("scene01.lua: setup()")
    hello_actor = scene:get_base_actor(scene:add_base_actor());
    hello_component = hello_actor:get_draw2d_component(
                          hello_actor:add_draw2d_component())
    hello_actor:set_position(vector3.new(0, 0, 0))
    hello_texture = add_texture();
    texture_fill_color(hello_texture, color.new(1, 0, 0, 1), "red")
    hello_component:create(hello_texture, 1.0, "SPRITE")
    print(utility.vec3_plus(vector3.new(0, 0, 0), vector3.new(1, 1, 1)).x)
    print("scene01.lua: end setup()")
end

function update()
    --    print("scene01.lua: update()") 
end
