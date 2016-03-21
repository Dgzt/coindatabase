import { Injectable }               from 'angular2/core';
import { Http, Response, Headers }  from 'angular2/http';
import { Observable }               from 'rxjs/Observable';

import 'rxjs/add/operator/map';
import 'rxjs/add/operator/catch';

import { Country }                  from './country';
import { COUNTRIES }                from './mock-countries'; 

@Injectable()
export class CountryService {
    
    constructor (private _http: Http) {}
    
    getCountries() {
        return Promise.resolve(COUNTRIES);
    }
    
    save(country : Country){
        var headers = new Headers();
        headers.append('Content-Type', 'application/json');
        
        return this._http.post(
                'api/country/save', 
                JSON.stringify(country),
                { headers: headers }
            )
            .map(res => <Country> res.json())
            .catch(this.handleError);
    }
    
    private handleError (error: Response) {
        // We may send the error to some remote logging infrastructure
        // instead of just logging it to the console
        console.error(error);
        return Observable.throw(error.json().error || 'Server error');
  }
}
