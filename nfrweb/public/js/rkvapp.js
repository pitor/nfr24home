var rkvApp = angular.module('rkvApp', ['ngRoute']);
var urlRex = /^\/rpc\//;


rkvApp.factory(
    'rpcInterceptor', function($q) {
	return {
	    'response': function(response) {
		if(!urlRex.test( response.config.url))
		    return response;

		return response;
		if( response.status >= 200 && response.status < 300)
		    return response.data;
		else
		    return $q.reject( response );
	    },

	    // optional method
	    'responseError': function(rejection) {
		return $q.reject(rejection);
	    }
	    
	};
    });


rkvApp.config(
    function($httpProvider) {
	$httpProvider.interceptors.push('rpcInterceptor');
    }
);
