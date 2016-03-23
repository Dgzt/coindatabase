package hu.dgzt.coindatabase.repositories;

import java.util.List;

import org.springframework.data.jpa.repository.Query;
import org.springframework.data.repository.CrudRepository;

import hu.dgzt.coindatabase.model.Country;

/**
 * The repository for {@link Country}.
 * 
 * @author Dgzt
 */
public interface CountryRepository extends CrudRepository<Country, String>{

	/**
	 * Return with the sorted all country.
	 */
	@Query("SELECT c FROM Country AS c ORDER BY c.name")
	List<Country> findAll();
}
