require 'rake/clean'

cxx      = ENV['CXX']
incflags = "-I."
cxxflags = "-std=c++11 #{incflags} -Wall -O3 -march=native"
tests    = FileList["test/*"].map{|f| f.sub("test", "out").ext("run")}

task :default => tests

task :out do
	unless File.directory?("out")
		sh "mkdir out"
	end
end

tests.each do |f|
	file f => :out do
		sh "#{cxx} #{cxxflags} -o #{f} #{f.sub('out', 'test').ext('cpp')}"
	end
end

task :clobber => :out do
	sh "rm -rf out/*"
end
