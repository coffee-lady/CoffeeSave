var WebFilestorage = {

    $WebFileStorage: {
        _cstr: null,

        getLocalStorageSafe: function() {
            try {
                if (window === null || window.localStorage == undefined) {
                    console.log("cant access local storage");
                    return null;
                }

                return window.localStorage
            } catch (e) {
                console.log("error get local storage");
            }

            return null;
        },

        load: function(key) {
            let storage = WebFileStorage.getLocalStorageSafe();

            if (storage === null) {
                console.log("cant access local storage");
                return null;
            }

            if (key == null) {
                console.log("Cant save for null key");
                return null;
            }

            return storage.getItem(key);
        },

        remove: function(key) {
            let storage = WebFileStorage.getLocalStorageSafe();

            if (storage === null) {
                console.log("cant access local storage");
                return null;
            }

            if (key == null) {
                console.log("Cant save for null key");
                return null;
            }

            storage.removeItem(key);
        },

        obfs: function(input, key, n) {
            key = key || 13;
            n = n || 126;

            var chars = input.split('');

            for (var i = 0; i < chars.length; i++) {
                var c = chars[i].charCodeAt(0);

                if (c <= n) {
                    chars[i] = String.fromCharCode((chars[i].charCodeAt(0) + key) % n);
                }
            }

            return chars.join('');
        },

        defs: function(input, key, n) {
            key = key || 13;
            n = n || 126;

            return WebFileStorage.obfs(input, n - key);
        },

        pointerToString: function(value) {
            //return Pointer_stringify(value);
            return UTF8ToString(value);
        }
    },

    WebFilestorage_save: function(cKey, cValue) {
        var key = WebFileStorage.pointerToString(cKey);
        var value = WebFileStorage.pointerToString(cValue);
        let storage = WebFileStorage.getLocalStorageSafe();

        //console.log("save to " + key + " content " + value);

        if (storage === null) {
            console.log("cant access local storage");
            return;
        }

        if (key == null) {
            console.log("Cant save for null key");
            return;
        }

        value = value || "";

        var coded = WebFileStorage.obfs(value);

        storage.setItem(key, coded);
    },

    WebFilestorage_load: function(cKey) {
        var key = WebFileStorage.pointerToString(cKey);

        //console.log("load from " + key);
        var result = WebFileStorage.load(key);

        try {
            var decode = WebFileStorage.defs(result);
            var json_val = JSON.parse(decode);
            if (json_val != null) {
                result = decode;
            }
        } catch (e) {}

        //console.log(result);

        if (WebFileStorage._cstr != null) {
            Module._free(WebFileStorage._cstr);
            WebFileStorage._cstr = null;
        }

        if (result != null && result != '') {
            WebFileStorage._cstr = allocate(intArrayFromString(result), "i8", ALLOC_NORMAL);
        }

        //console.log(WebFileStorage._cstr);
        return WebFileStorage._cstr;
    },

    WebFilestorage_remove: function(cKey) {
        var key = WebFileStorage.pointerToString(cKey);

        //console.log("remove from " + key);
        WebFileStorage.remove(key);
    }
}

autoAddDeps(WebFilestorage, '$WebFileStorage');
mergeInto(LibraryManager.library, WebFilestorage);
