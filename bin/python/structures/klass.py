from __future__ import absolute_import
from re import sub

from ..defaults.method_bodies import *
from ..defaults.header_guard import __guard__


class Class(object):

    def __init__(self, name):
        self.name = name
        self.guard = __guard__.format(GUARD_NAME=name)
        self.public = dict()
        self.private = dict()
        self.attributes = dict()
        self.supported_methods = set()
        object.__setattr__(self, self._get, __http_get_not_supported__)
        object.__setattr__(self, self._post, __http_post_not_supported__)
        object.__setattr__(self, self._patch, __http_patch_not_supported__)
        object.__setattr__(self, self._put, __http_put_not_supported__)
        object.__setattr__(self, self._delete, __http_delete_not_supported__)

    @property
    def get(self):
        return self._get

    @get.setter
    def get(self, body):
        self.supported_methods.add("GET")
        self._get = body

    @property
    def post(self):
        return self._post

    @post.setter
    def post(self, body):
        self.supported_methods.add("POST")
        self._post = body

    @property
    def patch(self):
        return self._patch

    @patch.setter
    def patch(self, body):
        self.supported_methods.add("PATCH")
        self._patch = body

    @property
    def put(self):
        return self._put

    @put.setter
    def put(self, body):
        self.supported_methods.add("PUT")
        self._put = body

    @property
    def delete(self):
        return self._delete

    @delete.setter
    def delete(self, body):
        self.supported_methods.add("DELETE")
        self._delete = body

    def format_unsupported_method(self, method):
        return sub(
                "  +",
                "",
                sub(
                    "{}",
                    "",
                    method.format(*self.supported_methods)
                )
        )
