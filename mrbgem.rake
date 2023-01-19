MRuby::Gem::Specification.new('mruby-ode') do |spec|
    spec.license = 'BSD-4-Clause'
    spec.author  = 'Jose A. Ramos'
    spec.summary = 'Open Dynamics Engine bindings'

    # spec.version = '0.0.1'

    # Install ode separately
    # See INSTALL.txt at https://bitbucket.org/odedevs/ode/src/master/
    spec.linker.libraries << "ode"

    # Very likely too platform specific, revise later
    spec.linker.library_paths << "/usr/local/lib"
    spec.cc.include_paths << "/usr/local/include
  end