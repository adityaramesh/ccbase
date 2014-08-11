require 'rake/clean'

cxx          = ENV['CXX']
boost        = ENV['BOOST_INCLUDE_PATH']
sphinx_build = ""

if ENV.key?('PYTHON_BIN')
	sphinx_build = "#{ENV['PYTHON_BIN']}sphinx-build"
end

langflags  = "-std=c++11"
wflags     = "-Wall -Wextra -pedantic -Wno-missing-field-initializers"
archflags  = "-march=native"
incflags   = "-I include -isystem #{boost}"
ldflags    = ""

if cxx.include? "clang"
	optflags     = "-Ofast -fno-fast-math -flto"
	lib_optflags = "-Ofast -fno-fast-math -flto"
elsif cxx.include? "g++"
	optflags      = "-Ofast -fno-fast-math -flto"
	lib_optflags  = "-Ofast -fno-fast-math -flto"
end

if RUBY_PLATFORM.include? "linux"
	ldflags = "-ldl"
end

cxxflags = "#{langflags} #{wflags} #{archflags} #{incflags} #{optflags}"

lib_ppflags   = "-DCCBASE_EXPORT_SYMBOLS"
lib_confflags = ""

if RUBY_PLATFORM.include? "linux"
	lib_confflags = "-shared -fpic -fvisibility=hidden -fvisibility-inlines-hidden"
elsif RUBY_PLATFORM.include? "darwin"
	lib_confflags = "-dynamiclib -fvisibility=hidden -fvisibility-inlines-hidden"
end

lib_cxxopts  = "#{langflags} #{wflags} #{archflags} #{incflags} #{lib_optflags}"
lib_cxxflags = "#{lib_cxxopts} #{lib_ppflags} #{lib_confflags}"

dirs  = ["out/test", "out/libraries", "out/reference"]
tests = ["out/test/formatter_test.run"]#FileList["source/test/*"].map{|f| f.sub("source", "out").ext("run")}
libs  = FileList["source/libraries/*"].map{|f| f.sub("source", "out").ext("lib")}

if RUBY_PLATFORM.include? "linux"
	refs = FileList["source/reference/linux/*"].map{|f| f.sub("source", "out").
		sub("linux/", "").ext("run")}
elsif RUBY_PLATFORM.include? "darwin"
	refs = FileList["source/reference/os_x/*"].map{|f| f.sub("source", "out").
		sub("os_x/", "").ext("run")}
end

multitask :default => dirs + tests + libs

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

task "docs" do
	sh "#{sphinx_build} -b html docs ../gh-pages"
end

dirs.each do |d|
	directory d
end

libs.each do |f|
	src = f.sub("out", "source").ext("cpp")
	file f => [src] + dirs do
		sh "#{cxx} #{lib_cxxflags} -o #{f} #{src}"
	end
end

tests.each do |f|
	src = f.sub("out", "source").ext("cpp")
	file f => [src] + dirs do
		sh "#{cxx} #{cxxflags} -o #{f} #{src} #{ldflags}"
	end
end

refs.each do |f|
	if RUBY_PLATFORM.include? "linux"
		src = f.sub("out", "source").sub("ref", "reference/linux").ext("cpp")
	elsif RUBY_PLATFORM.include? "darwin"
		src = f.sub("out", "source").sub("ref", "reference/os_x").ext("cpp")
	end
	file f => [src] + dirs do
		sh "#{cxx} #{cxxflags} -o #{f} #{src} #{ldflags}"
	end
end

task :clobber => dirs do
	FileList["out/test/*.run"].each{|f| File.delete(f)}
	FileList["out/libraries/*"].each{|f| File.delete(f)}
	FileList["out/reference/**/*.run"].each{|f| File.delete(f)}
end
