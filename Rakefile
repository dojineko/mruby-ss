MRUBY_CONFIG=File.expand_path(ENV["MRUBY_CONFIG"] || "build_config.rb")

file :mruby do
  sh "git clone git://github.com/mruby/mruby.git"
end

desc "compile binary"
task :compile => [:mruby, :iproute] do
  sh "cd mruby && MRUBY_CONFIG=#{MRUBY_CONFIG} rake all"
end

desc "test"
task :test => [:mruby] do
  sh "cd mruby && MRUBY_CONFIG=#{MRUBY_CONFIG} rake all test"
end

desc "cleanup"
task :clean do
  sh "cd mruby && rake deep_clean"
end

desc "run docker"
task :docker do
  sh "docker build -t mruby:ss ."
  sh "docker run -v `pwd`:/tmp/mruby-ss -w /tmp/mruby-ss -it mruby:ss"
end

task :default => :test
