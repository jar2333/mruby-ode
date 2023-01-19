MRuby::Gem::Specification.new('mruby-eval') do |spec|
    spec.license = 'BSD-4-Clause'
    spec.author  = 'Jose A. Ramos'
    spec.summary = 'Open Dynamics Engine library'

    # spec.version = '0.0.1'

    # Install ode separately
    # See INSTALL.txt at https://bitbucket.org/odedevs/ode/src/master/
    spec.linker.libraries << "ode"
  end