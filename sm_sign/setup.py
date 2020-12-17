from setuptools import setup, dist
from setuptools.command.install import install
import os

class BinaryDistribution(dist.Distribution):
    def has_ext_modules(foo):
        return True

class PostInstallCommand(install):
    def run(self):
        install.run(self)
        if not os.path.isdir(self.install_scripts):
            os.makedirs(self.install_scripts)
        package_dir = os.path.dirname(os.path.abspath(__file__))
        binary_dir = os.path.join(package_dir, "bin");
        binary = "sm_sign"
        source = os.path.join(package_dir, "sm_sign/__main__.py")
        target = os.path.join(self.install_scripts, "sm_sign")
        if os.path.isfile(target):
            os.remove(target)
        self.copy_file(source, target)

this_directory = os.path.abspath(os.path.dirname(__file__))
with open(os.path.join(this_directory, 'README.md')) as f:
    long_description = f.read()

setup(
    name='sm_sign',
    package_data={'sm_sign': ['_mod_sm.so', 'LICENSE']},
    version='0.1.0',
    description="A module and command-line utility to extract structured data from HTML",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url='https://github.com/Nut-Guo/sm_sign',
    author='Nut Guo',
    author_email='qinsiliang18@mails.ucas.ac.cn',
    include_package_data=True,
    distclass=BinaryDistribution,
    cmdclass={'install': PostInstallCommand},
    packages=['sm_sign'],
    classifiers=[
        'Development Status :: 1 - Planning',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: Apache Software License',
        'Operating System :: POSIX :: Linux',
        'Programming Language :: C++',
        'Topic :: Security :: Cryptography',
        'Topic :: Software Development :: Libraries :: Python Modules',
    ],
    keywords='SM sign apk',
    project_urls={
        'Github': 'https://github.com/Nut-Guo/sm_sign',
    },
)