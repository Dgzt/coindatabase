package hu.dgzt.coindatabase.service;

import java.util.List;

import hu.dgzt.coindatabase.model.Country;

/**
 * The service for {@link Country}
 * 
 * @author Dgzt
 */
public interface CountryService {
	
	/**
	 * Save the given country.
	 * 
	 * @param country - The country.
	 * @return The saved country.
	 */
	Country save(final Country country);
	
	/**
	 * Return with the all country.
	 */
	List<Country> findAll();
	
}
