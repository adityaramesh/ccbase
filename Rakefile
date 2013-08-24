require 'rake/clean'

cxx       = ENV['CXX']
boost     = ENV['BOOST_INCLUDE_PATH']
langflags = "-std=c++11"
wflags    = "-Wall -Wno-return-type-c-linkage"
archflags = "-march=native"
incflags  = "-I. -I#{boost}"
optflags  = "-O3"
ldflags   = ""

if RUBY_PLATFORM.include? "linux"
	ldflags = "-ldl"
end

cxxflags  = "#{langflags} #{wflags} #{archflags} #{incflags} #{optflags}"

lib_ppflags   = "-DCCBASE_EXPORT_SYMBOLS"
lib_confflags = ""

if RUBY_PLATFORM.include? "linux"
	lib_confflags = "-shared -fpie -fvisibility=hidden"
elsif RUBY_PLATFORM.include? "darwin"
	lib_confflags = "-dynamiclib -fvisibility=hidden"
end

lib_cxxflags = "#{cxxflags} #{lib_ppflags} #{lib_confflags}"

dirs  = ["out/test", "out/lib"]
tests = FileList["src/test/*"].map{|f| f.sub("src", "out").ext("run")}
libs  = FileList["src/lib/*"].map{|f| f.sub("src", "out").ext("lib")}

task :default => dirs + tests + libs

task "check" => tests do
	tests.each do |f|
		sh "./#{f}"
	end
end

dirs.each do |d|
	directory d
end

libs.each do |f|
	src = f.sub("out", "src").ext("cpp")
	file f => [src] + dirs do
		sh "#{cxx} #{lib_cxxflags} -o #{f} #{src}"
	end
end

tests.each do |f|
	src = f.sub("out", "src").ext("cpp")
	file f => [src] + dirs do
		sh "#{cxx} #{cxxflags} -o #{f} #{src} #{ldflags}"
	end
end

task :clobber => dirs do
	FileList["out/test/*.run"].each{ |f| File.delete(f) if File.exist?(f) }
	FileList["out/lib/*.lib"].each{ |f| File.delete(f) if File.exist?(f) }
end
