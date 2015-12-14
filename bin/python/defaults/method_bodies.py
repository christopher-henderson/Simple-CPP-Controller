__not_supported__ = """\
    Response {METHOD}() {
        std::map headers();

        headers.insert(std::pair<char*, char*>("Allow", "{} {} {} {} {}");
        return Response().
            setHTTPCode(405).
            addHeaders(headers).
            setBody(Json::Value())
    }
"""

__http_get_not_supported__ = __not_supported__.format(METHOD="get")

__http_post_not_supported__ = __not_supported__.format(METHOD="post")

__http_patch_not_supported__ = __not_supported__.format(METHOD="patch")

__http_put_not_supported__ = __not_supported__.format(METHOD="put")

__http_delete_not_supported__ = __not_supported__.format(METHOD="delete")