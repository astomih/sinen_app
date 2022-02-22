local utility = require("utility")
function move_to_player()
    player_pos = player:get_position()
    before = enemy:get_position()
    dir = utility.vec3_minus(player_pos, before)
    dir:normalize();
    dir = utility.vec3_multi_float(dir, 10 * delta_time)
    atan2 = -math.atan(dir.x, dir.y)
    q = quaternion.new(vector3.new(0, 0, 1), atan2);
    enemy:set_rotation(q);
    enemy:move(dir);
    enemy_body:collision(before)
end
