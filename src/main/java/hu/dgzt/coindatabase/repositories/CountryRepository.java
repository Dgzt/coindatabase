package hu.dgzt.coindatabase.repositories;

import org.springframework.data.repository.CrudRepository;

import hu.dgzt.coindatabase.model.Country;

/**
 * The repository for {@link Country}.
 * 
 * @author Dgzt
 */
public interface CountryRepository extends CrudRepository<Country, String>{

}
