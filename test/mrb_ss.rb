##
## SS Test
##

assert("SS#hello") do
  t = SS.new "hello"
  assert_equal("hello", t.hello)
end

assert("SS#bye") do
  t = SS.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("SS.hi") do
  assert_equal("hi!!", SS.hi)
end
