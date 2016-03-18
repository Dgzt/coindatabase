import { Injectable } from 'angular2/core';
import { Country } from './country';
import { COUNTRIES } from './mock-countries'; 

@Injectable()
export class CountryService {
    
    getCountries() {
        return Promise.resolve(COUNTRIES);
    }
    
}
