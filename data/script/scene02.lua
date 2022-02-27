local tex = {}
local draw_obj = {}
function setup()
    tex = texture.new()
    tex:load("data/texture/scene02.png")
    draw_obj = draw2d.object.new()
    draw_obj:set_texture(tex)
end
function update() print("scene02.lua: update()") end

