require 'rake/clean'

cxx       = ENV['CXX']
langflags = "-std=c++11"
wflags    = "-Wall"
archflags = "-march=native"
incflags  = "-I."
ppflags   = ""
optflags  = "-O3"
cxxflags  = "#{langflags} #{wflags} #{archflags} #{incflags} #{ppflags} #{optflags}"

dll_ppflags   = "-DCCBASE_EXPORT_SYMBOLS"
dll_confflags = "-dynamiclib -fvisibility=hidden"
dll_cxxflags  = "#{cxxflags} #{dll_ppflags} #{dll_confflags}"

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
	tests.each{ |f| File.delete(f) }
	libs.each{ |f| File.delete(f) }
end

outdirs.each do |d|
	directory d
end

libs.each do |f|
	file f => headers + outdirs do
		sh "#{cxx} #{dll_cxxflags} -o #{f} #{f.sub('out', 'src').ext('cpp')}"
	end
end

tests.each do |f|
	file f => libs + headers + outdirs do
		sh "#{cxx} #{cxxflags} -o #{f} #{f.sub('out', 'test').ext('cpp')}"
	end
end
