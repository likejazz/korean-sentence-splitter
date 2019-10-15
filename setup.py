import platform

from Cython.Build import cythonize

# from distutils.core import setup
from setuptools import setup
from distutils.extension import Extension

from os import path

# Read the contents of your README file
this_directory = path.abspath(path.dirname(__file__))
with open(path.join(this_directory, 'README.md'), encoding='utf-8') as f:
    long_description = f.read()

# Build params for each platforms.
if platform.system() == 'Linux':
    extra_compile_args=['-std=c++11']
    extra_link_args=[]
elif platform.system() == 'Darwin':
    extra_compile_args=['-std=c++11', '-stdlib=libc++']
    extra_link_args=['-stdlib=libc++']

ext = [
    Extension('kss',
              sources=[
                  'kss.pyx',
                  'sentence_splitter.cpp',
              ],
              language='c++',
              extra_compile_args=extra_compile_args,
              extra_link_args=extra_link_args,
              include_dirs=["."],
              )
]

setup(name='kss',
      version='1.2.5',
      author='Sang-Kil Park',
      author_email='skpark1224@hyundai.com',
      url='https://github.com/likejazz/korean-sentence-splitter',
      license='BSD 3-Clause "New" or "Revised" License',
      description='Split Korean text into sentences using heuristic algorithm.',
      long_description=long_description,
      long_description_content_type='text/markdown',
      platforms=['any'],
      classifiers=[
          "Programming Language :: Python :: 3",
          "License :: OSI Approved :: BSD License",
          "Operating System :: OS Independent",
      ],
      ext_modules=cythonize(ext, language_level=3)
      )
