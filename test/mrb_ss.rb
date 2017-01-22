##
## SS Test
##

assert("SS::TCP#listen?") do
  SS::TCP.new('127.0.0.1', 80).listen?
  SS::TCP.new('127.0.0.1', 81).listen?
end
