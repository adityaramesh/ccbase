.. _ccbase-filesystem-module:
.. default-domain:: cpp

The Filesystem Module
=====================

To use this module, include ``ccbase/filesystem.hpp``. Please note that this
module currently works on OS X and Linux only. 

Overview
--------

Using this header, you can do the following **without any static library
dependencies.** ::

        // Iterate over all JPG files in the `dat` directory after applying a
        // Bash glob filter.
	for (const auto& e : cc::match_files("dat/frame_[abc]*.jpg")) {
		cc::println(e.name());
	}

If you do not need a glob filter, then use :func:`match_files` instead. This
function is more efficient, since it does not pass each file name through a glob
filter. Note that ``.``, ``..``, and other dotfiles will appear in the range of
matched files. You will need to check for these explicitly if you do not want to
process them. Here's an example: ::

        for (const auto& e : cc::list_files("dat")) {
                if (!e.starts_with('.')) {
                        cc::println(e.name());
                }
        }

Reference
---------

.. namespace:: cc

.. class:: file_type : unsigned char

   This is an ``enum class`` used to indicate the type of the current
   :class:`directory_entry`.

   .. member:: file_type block_device
   .. member:: file_type character_device
   .. member:: file_type directory
   .. member:: file_type fifo
   .. member:: file_type symbolic_link
   .. member:: file_type regular
   .. member:: file_type socket
   .. member:: file_type unknown

.. class:: directory_entry

   This class is used to store the information pertaining to a directory entry.

   .. function:: const boost::string_ref path() const noexcept

      Returns the path to the file referenced by this directory entry.

   .. function:: const boost::string_ref name() const noexcept

      Returns the name of the file referenced by this directory entry.

   .. function:: file_type type() const noexcept

      Returns the type of the file referenced by this directory entry.

.. function:: std::ostream& operator<<(std::ostream& os, const directory_entry& e)

   Writes the representation of the given :class:`directory_entry` to the given
   :class:`ostream` object. This representation consists of the name and type of
   the file referenced by the directory entry. Example output: ::

        {name: "text.txt", type: "regular file"}

.. function:: Range list_files(const boost::string_ref path)

   Returns a range object that can be used to traverse the contents of the
   directory at *path*.

   :throws: :class:`std::runtime_error` if an IO error occurs while accessing the directory.

.. function:: Range match_files(const boost::string_ref glob)

   Returns a range object that can be used to traverse the contents of the
   directory referenced by *glob*. Any characters following the last occurrence
   of the platform directory separator in *glob* are used interpreted as a glob
   pattern. This glob pattern is used to filter the files in the directory by
   name.

   Note that recursive directory enumeration is currently unsupported.

   :throws: :class:`std::runtime_error` if an IO error occurs while accessing the directory.
