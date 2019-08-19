

/**
 * Copyright 2015 Evernote Corporation. All rights reserved.
 *
 * Represents the different copy and images we show when the user enters a state where
 * the NoteList is empty.
 */
define(['require','react','resolve!i18n','focus-drawer-HelpIllustration','css!focus/NotesView/EmptyState'],function (require) {
  

  var React = require('react');
  var i18n = require('resolve!i18n');

  var HelpIllustration = require('focus-drawer-HelpIllustration');
  require('css!focus/NotesView/EmptyState');

  function prefixedClass(suffix) {
    return 'focus-NotesView-EmptyState-' + suffix;
  }

  var EmptyState = React.createClass({
    displayName: 'EmptyState',

    propTypes: {
      notesListDisplayState: React.PropTypes.string.isRequired,
      searchQuery: React.PropTypes.string,
      selectedTagName: React.PropTypes.string,
      totalNotes: React.PropTypes.number.isRequired
    },

    isNotesEmptyState: function isNotesEmptyState() {
      return this.props.totalNotes <= 1 && (this.props.notesListDisplayState === 'NOTEBOOK' || this.props.notesListDisplayState === 'ALL_NOTES');
    },

    isSearchEmptyState: function isSearchEmptyState() {
      return this.props.totalNotes === 0 && this.props.notesListDisplayState === 'SEARCH' && this.props.searchQuery;
    },

    isTagsEmptyState: function isTagsEmptyState() {
      return this.props.totalNotes === 0 && this.props.notesListDisplayState === 'TAG' && this.props.selectedTagName;
    },

    render: function render() {
      if (!this.isNotesEmptyState() && !this.isSearchEmptyState() && !this.isTagsEmptyState()) {
        return null;
      }

      var emptyState = null;
      switch (this.props.notesListDisplayState) {
        case 'NOTEBOOK':
        case 'ALL_NOTES':
          emptyState = React.createElement(
            HelpIllustration,
            {
              baseClass: 'notes',
              body: i18n.L('Focus.notesView.empty.body'),
              imageClass: prefixedClass('HelpImageNotes')
            },
            React.createElement('span', { dangerouslySetInnerHTML: { __html: i18n.L('Focus.notesView.empty.header', ['<span class="newNoteIcon"></span>']) }
            })
          );
          break;
        case 'TAG':
          emptyState = React.createElement(
            HelpIllustration,
            {
              baseClass: 'tags',
              imageClass: prefixedClass('HelpImageTags')
            },
            i18n.L('Focus.notesView.empty.tags.header', [this.props.selectedTagName])
          );
          break;
        case 'SEARCH':
          emptyState = React.createElement(
            HelpIllustration,
            {
              baseClass: 'search',
              imageClass: prefixedClass('HelpImageSearch')
            },
            i18n.L('Focus.notesView.empty.search.header', [this.props.searchQuery])
          );
          break;
      }
      return React.createElement(
        'div',
        { className: prefixedClass('container') },
        emptyState
      );
    }
  });

  return EmptyState;
});