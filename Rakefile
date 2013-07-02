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

tests = FileList["test/*"].map{|f| f.sub("test", "out").ext("run")}
libs  = FileList["lib/src/*"].map{|f| f.sub("src", "out").ext("dll")}

task :default => libs + tests

task :out do
	unless File.directory?("out")
		sh "mkdir out"
	end
end

libs.each do |f|
	file f => :out do
		sh "#{cxx} #{dll_cxxflags} -o #{f} #{f.sub('out', 'src').ext('cpp')}"
	end
end

tests.each do |f|
	file f => :out do
		sh "#{cxx} #{cxxflags} -o #{f} #{f.sub('out', 'test').ext('cpp')}"
	end
end

task :clobber => :out do
	sh "rm -rf out/*"
	sm "rm -rf lib/out/*"
end
