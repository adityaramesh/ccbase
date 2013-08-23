require 'rake/clean'

cxx       = ENV['CXX']
boost     = ENV['BOOST_INCLUDE_PATH']
langflags = "-std=c++11 -stdlib=libc++"
wflags    = "-Wall -Wno-return-type-c-linkage"
archflags = "-march=native"
incflags  = "-I. -I#{boost}"
ppflags   = ""
optflags  = "-O3"
ldflags   = ""

if RUBY_PLATFORM.include? "linux"
	ldflags = "-ldl"
end

cxxflags  = "#{langflags} #{wflags} #{archflags} #{incflags} #{ppflags} #{optflags}"

dll_ppflags   = "-DCCBASE_EXPORT_SYMBOLS"
dll_confflags = ""

if RUBY_PLATFORM.include? "linux"
	dll_confflags = "-shared -fpie -fvisibility=hidden"
elsif RUBY_PLATFORM.include? "darwin"
	dll_confflags = "-dynamiclib -fvisibility=hidden"
end

dll_cxxflags = "#{cxxflags} #{dll_ppflags} #{dll_confflags}"

outdirs = ["out", "lib/out"]
headers = FileList["ccbase/*"]
tests   = FileList["test/*"].map{|f| f.sub("test", "out").ext("run")}
libs    = FileList["lib/src/*"].map{|f| f.sub("src", "out").ext("dll")}

task :default => tests

task "tests" => tests do
	tests.each do |f|
		sh "./#{f}"
	end
end

task :clobber => outdirs do
	tests.each{ |f| File.delete(f) if File.exist?(f) }
	libs.each{ |f| File.delete(f) if File.exist?(f) }
end

outdirs.each do |d|
	directory d
end

libs.each do |f|
	src = f.sub("out", "src").ext("cpp")
	file f => [src] + headers + outdirs do
		sh "#{cxx} #{dll_cxxflags} -o #{f} #{src}"
	end
end

tests.each do |f|
	src = f.sub("out", "test").ext("cpp")
	file f => [src] + libs + headers + outdirs do
		sh "#{cxx} #{cxxflags} -o #{f} #{src} #{ldflags}"
	end
end
