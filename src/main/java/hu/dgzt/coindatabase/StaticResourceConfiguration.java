package hu.dgzt.coindatabase;

import org.springframework.context.annotation.Configuration;
import org.springframework.web.servlet.config.annotation.EnableWebMvc;
import org.springframework.web.servlet.config.annotation.ResourceHandlerRegistry;
import org.springframework.web.servlet.config.annotation.WebMvcConfigurerAdapter;

/**
 * The configuration for static resources.
 * 
 * @author Dgzt
 */
@Configuration
public class StaticResourceConfiguration extends WebMvcConfigurerAdapter {

	/**
	 * Add the resources to the resources handler:
	 * <ul>
	 * 	<li><b>node_modules</b> directory</li>
	 * </ul>
	 */
	@Override
	public void addResourceHandlers(ResourceHandlerRegistry registry) {
		super.addResourceHandlers(registry);
		
		registry.addResourceHandler("/node_modules/**").addResourceLocations("classpath:/public/node_modules/");
	}
}
