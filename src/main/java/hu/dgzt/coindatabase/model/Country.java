package hu.dgzt.coindatabase.model;

import java.util.UUID;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

/**
 * The entity for country.
 * 
 * @author Dgzt
 */
@Entity(name = "Country")
@Table(name = "countries")
public class Country {
	
	// --------------------------------------------------
	// ~ Private members
	// --------------------------------------------------
	
	@Id
	@Column(name = "id", length = 40)
	private String id = UUID.randomUUID().toString();;

	/** The name. */
	@Column(name = "name", length = 128)
	private String name;
	
	// --------------------------------------------------
	// ~ Getter / Setter methods
	// --------------------------------------------------
	
	public String getId() {
		return id;
	}
	
	public void setId(final String id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(final String name) {
		this.name = name;
	}

}
