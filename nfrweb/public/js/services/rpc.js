rkvApp.factory('RPCService', ['$http', function( $http ){
    var service = {
	getVals: function() {
	    return $http.get('/rpc/vals');
	},
	getSensors: function() {},
    };

    return service;
}]);