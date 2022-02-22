local function vec3_plus(a, b)
    return vector3.new(a.x + b.x, a.y + b.y, a.z + b.z)
end
local function vec3_minus(a, b)
    return vector3.new(a.x - b.x, a.y - b.y, a.z - b.z)
end
local function vec3_multi(a, b)
    return vector3.new(a.x * b.x, a.y * b.y, a.z * b.z)
end
local function vec3_multi_float(a, b)
    return vector3.new(a.x * b, a.y * b, a.z * b)
end
return {
    vec3_plus = vec3_plus,
    vec3_minus = vec3_minus,
    vec3_multi = vec3_multi,
    vec3_multi_float = vec3_multi_float
}
