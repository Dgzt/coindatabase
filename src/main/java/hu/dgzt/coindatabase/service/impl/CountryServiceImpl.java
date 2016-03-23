package hu.dgzt.coindatabase.service.impl;

import java.util.List;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Transactional;

import hu.dgzt.coindatabase.model.Country;
import hu.dgzt.coindatabase.repositories.CountryRepository;
import hu.dgzt.coindatabase.service.CountryService;

/**
 * The implementation for {@link CountryService}.
 * 
 * @author Dgzt
 */
@Service
public class CountryServiceImpl implements CountryService{

	// --------------------------------------------------
	// ~ Repositories
	// --------------------------------------------------
	
	@Autowired
	private CountryRepository countryRepository;
	
	// --------------------------------------------------
	// ~ Override methods
	// --------------------------------------------------
	
	/**
	 * {@inheritDoc}
	 */
	@Override
	@Transactional(readOnly = false)
	public Country save(final Country country) {
		return countryRepository.save(country);
	}

	/**
	 * {@inheritDoc}
	 */
	@Override
	public List<Country> findAll() {
		return countryRepository.findAll();
	}

}
