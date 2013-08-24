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
	lib_confflags = "-shared -fpic -fvisibility=hidden"
elsif RUBY_PLATFORM.include? "darwin"
	lib_confflags = "-dynamiclib -fvisibility=hidden"
end

lib_cxxflags = "#{cxxflags} #{lib_ppflags} #{lib_confflags}"

dirs  = ["out/test", "out/lib", "out/ref"]
tests = FileList["src/test/*"].map{|f| f.sub("src", "out").ext("run")}
libs  = FileList["src/lib/*"].map{|f| f.sub("src", "out").ext("lib")}

if RUBY_PLATFORM.include? "linux"
	refs = FileList["src/ref/linux/*"].map{|f| f.sub("src", "out").
		sub("linux/", "").ext("run")}
elsif RUBY_PLATFORM.include? "darwin"
	refs = FileList["src/ref/os_x/*"].map{|f| f.sub("src", "out").
		sub("os_x/", "").ext("run")}
end

task :default => dirs + tests + libs

task "refs" => dirs + refs

task "check" => dirs + tests + libs do
	(tests - ["out/test/unit_test_test.run"]).each do |f|
		r = `./#{f} -v medium`
		if r.include? "Failure"
			puts "The test \"#{f}\" failed! Please submit a bug report."
			puts r
		end
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

refs.each do |f|
	if RUBY_PLATFORM.include? "linux"
		src = f.sub("out", "src").sub("ref", "ref/linux").ext("cpp")
	elsif RUBY_PLATFORM.include? "darwin"
		src = f.sub("out", "src").sub("ref", "ref/os_x").ext("cpp")
	end
	file f => [src] + dirs do
		sh "#{cxx} #{cxxflags} -o #{f} #{src} #{ldflags}"
	end
end

task :clobber => dirs do
	FileList["out/test/*.run"].each{ |f| File.delete(f) if File.exist?(f) }
	FileList["out/lib/*.lib"].each{ |f| File.delete(f) if File.exist?(f) }
	FileList["out/ref/**/*.run"].each{ |f| File.delete(f) if File.exist?(f) }
end
