package hu.dgzt.coindatabase.controller;

import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RestController;

import hu.dgzt.coindatabase.model.Country;

/**
 * Controller for {@link Country}
 * 
 * @author Dgzt
 */
@RestController
@RequestMapping("/api/country")
public class CountryController {

	/**
	 * Save the given {@link Country} and return with the saved country.
	 * 
	 * @param newCountry - The saving country.
	 * @return The saved country.
	 */
	@RequestMapping(path = "/save", method = RequestMethod.POST)
	public Country save(final @RequestBody Country newCountry){
		System.out.println("New: " + newCountry.getName());
		
		return newCountry;
	}
}
