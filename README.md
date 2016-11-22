# mruby-ss   [![Build Status](https://travis-ci.org/dojineko/mruby-ss.svg?branch=master)](https://travis-ci.org/dojineko/mruby-ss)
SS class
## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'dojineko/mruby-ss'
end
```
## example
```ruby
p SS.hi
#=> "hi!!"
t = SS.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
